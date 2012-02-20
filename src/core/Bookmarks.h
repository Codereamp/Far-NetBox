//---------------------------------------------------------------------------
#ifndef BookmarksH
#define BookmarksH

#include "Classes.h"

//---------------------------------------------------------------------------
class THierarchicalStorage;
class TBookmarkList;
class TShortCuts;
//---------------------------------------------------------------------------
class TBookmarks : public nb::TObject
{
public:
    TBookmarks();
    virtual ~TBookmarks();

    void Load(THierarchicalStorage *Storage);
    void Save(THierarchicalStorage *Storage, bool All);
    void ModifyAll(bool Modify);
    void Clear();

    TBookmarkList *GetBookmark(const std::wstring Index);
    void SetBookmark(const std::wstring Index, TBookmarkList *value);
    TBookmarkList *GetSharedBookmarks();
    void SetSharedBookmarks(TBookmarkList *value);

private:
    nb::TStringList *FBookmarkLists;
    std::wstring FSharedKey;
    static std::wstring Keys[];

    void LoadLevel(THierarchicalStorage *Storage, const std::wstring Key,
                   int Index, TBookmarkList *BookmarkList);
};
//---------------------------------------------------------------------------
class TBookmarkList : public nb::TPersistent
{
    friend class TBookmarks;
    friend class TBookmark;
public:
    TBookmarkList();
    virtual ~TBookmarkList();

    void Clear();
    void Add(TBookmark *Bookmark);
    void Insert(size_t Index, TBookmark *Bookmark);
    void InsertBefore(TBookmark *BeforeBookmark, TBookmark *Bookmark);
    void MoveTo(TBookmark *ToBookmark, TBookmark *Bookmark, bool Before);
    void Delete(TBookmark *Bookmark);
    TBookmark *FindByName(const std::wstring Node, const std::wstring Name);
    TBookmark *FindByShortCut(nb::TShortCut ShortCut);
    virtual void Assign(nb::TPersistent *Source);
    void LoadOptions(THierarchicalStorage *Storage);
    void SaveOptions(THierarchicalStorage *Storage);
    void ShortCuts(TShortCuts &ShortCuts);

    size_t GetCount();
    TBookmark *GetBookmark(size_t Index);
    bool GetNodeOpened(const std::wstring Index);
    void SetNodeOpened(const std::wstring Index, bool value);

protected:
    size_t IndexOf(TBookmark *Bookmark);
    void KeyChanged(size_t Index);

    bool GetModified() { return FModified; }
    void SetModified(bool value) { FModified = value; }

private:
    nb::TStringList *FBookmarks;
    nb::TStringList *FOpenedNodes;
    bool FModified;
};
//---------------------------------------------------------------------------
class TBookmark : public nb::TPersistent
{
    friend class TBookmarkList;
public:
    TBookmark();

    virtual void Assign(nb::TPersistent *Source);

    std::wstring GetName() { return FName; }
    void SetName(const std::wstring value);
    std::wstring GetLocal() { return FLocal; }
    void SetLocal(const std::wstring value);
    std::wstring GetRemote() { return FRemote; }
    void SetRemote(const std::wstring value);
    std::wstring GetNode() { return FNode; }
    void SetNode(const std::wstring value);
    nb::TShortCut GetShortCut() { return FShortCut; }
    void SetShortCut(nb::TShortCut value);

protected:
    TBookmarkList *FOwner;

    static std::wstring BookmarkKey(const std::wstring Node, const std::wstring Name);
    std::wstring GetKey();

private:
    std::wstring FName;
    std::wstring FLocal;
    std::wstring FRemote;
    std::wstring FNode;
    nb::TShortCut FShortCut;

    void Modify(size_t OldIndex);
};
//---------------------------------------------------------------------------
#endif
